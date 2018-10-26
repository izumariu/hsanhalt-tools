$0==__FILE__&&abort("This is a library file. Run 'RUN.rb' instead.")

require "time"

class HSAnhaltICS

  @@lecture_struct = Struct.new(*%w( title lecturer start end location ).map(&:to_sym))

  private

  def group(s)

      grouped = []
      grouped << []

      while s.length > 0
        i = s.shift
        if grouped[-1].length > 0
          if !(grouped[-1][0].start == i.start && grouped[-1][0].end == i.end)
            grouped << []
          end
          grouped[-1] << i
        else
          grouped[-1] << i
        end
      end

      grouped_sorted = []

      # selection sort:
      while grouped.length > 0
        _minv = grouped[0][0].start # minimum value
        _mini = 0 # minimum value group index
        grouped.each_with_index do |g, i|
          if g[0].start < _minv
            _minv = g[0].start
            _mini = i
          end
        end
        grouped_sorted << grouped.delete_at(_mini)
      end

      grouped_sorted

  end


  public


  def initialize(s)

    unless s.class == Array && s.all?{ |event| event.is_a? @@lecture_struct }
      raise ArgumentError
    end

    @schedule = group s

  end



  attr_reader :schedule


  def self.normalize_chars(s)

    s.downcase!
    subs_chars = {
      ?Ä => ?ä,
      ?Ö => ?ö,
      ?Ü => ?ü,
      ?- => " "
    }
    subs_chars.each_pair{|k,v|s.gsub!(k,v)}
    s.gsub!(/\(.+\)/, "")
    s = s.split("").map do |c|
      #puts "Char '#{c}' has ord #{"%04x"%c.ord}"
      case c.ord
      when (0x00e0..0x00e5); ?A
      when 0x00e6; "AE"
      when 0x00e7; ?C
      when (0x00e8..0x00eb); ?E
      when (0x00ec..0x00ef); ?I
      when 0x00f0; ?D
      when 0x00f1; ?N
      when (0x00f2..0x00f6); ?O
      when 0x00f8; ?O
      when (0x00f9..0x00fc); ?U
      when 0x00fd; ?Y
      when 0x00df; "ss"
      else; c
      end
    end.join
    s.upcase.strip

  end


  def self.from(file, lecturers)

    content_raw = open(file, &:read).split(?\n)
    content = []

    ln = content_raw.map{ |i| i.match(%r{^BEGIN:VEVENT}) != nil }.index(true) || abort("No events found in #{file}...") # line number variable
    keyword_regex = Regexp.new(
      ?^ + %w(
        DTSTAMP: UID: DESCRIPTION: BEGIN:VEVENT DTSTART:
        DTEND: SUMMARY: LOCATION: END:VEVENT END:VCALENDAR
      ).join("|^")
    )

    content_raw[ln..-1].each do |l|
      if l.strip.match(keyword_regex)
        content << l.strip
      else
        content[-1] << l[1..-1] # whitespace stuff!
      end
    end

    ics_parsed = []
    eventmode = false
    ignored_words = Regexp.new %w(DTSTAMP UID DESCRIPTION).map{|i|"^#{i}"}.join(?|)

    content.each_with_index do |line_raw, line_number|

      line = line_raw.strip

      case line

      when /^BEGIN:VEVENT$/
        ics_parsed << @@lecture_struct.new
        eventmode = true

      when /^DTSTART:/
        eventmode||raise("Line #{ln+1} in #{file} is a #{line.split(?:)[0]}, but not inside of an event definition")
        ics_parsed[-1].start = Time.parse(line.split(?:)[1..-1].join(?:)).to_i

      when /^DTEND:/
        eventmode||raise("Line #{ln+1} in #{file} is a #{line.split(?:)[0]}, but not inside of an event definition")
        ics_parsed[-1].end = Time.parse(line.split(?:)[1..-1].join(?:)).to_i

      when /^SUMMARY:/
        eventmode||raise("Line #{ln+1} in #{file} is a #{line.split(?:)[0]}, but not inside of an event definition")
        lecture_info_startindex = (line =~ Regexp.new(lecturers.keys.join(?|)))

        begin
          line_cropped = line[lecture_info_startindex..-1]
        rescue ArgumentError => e
          puts [
            "BAD VALUE FOR RANGE",
            "RANGE VALUE: #{lecture_info_startindex.inspect}",
            "ICS LINE NUMBER: #{line_number}"
          ].map{|i|"ERRDUMP :: #{i}"}
          abort
        end

        _title = normalize_chars(line_cropped.split[1..-1].join(" "))

        if _title.split[0].match(/^[PUV](\/[PUV])*$/)
          _title = _title.split[1..-1].join(" ")
        end

        ics_parsed[-1].title = _title
        ics_parsed[-1].lecturer = normalize_chars(lecturers[line_cropped.split.first]||line_cropped.split.first)

      when /^LOCATION:/
        eventmode||raise("Line #{ln+1} in #{file} is a #{line.split(?:)[0]}, but not inside of an event definition")
        ics_parsed[-1].location = line.split(?:)[1..-1].join(?:)

      when /^END:VEVENT/
        eventmode = false

      when ignored_words; #eventmode||raise("Line #{ln+1} in #{file} is a #{line.split(?:)[0]}, but not inside of an event definition")
      when /^END:VCALENDAR/; break
      else;puts "U: #{line.inspect}"

      end

      ln += 1

    end

    new(ics_parsed)

  end


  def self.did_you_mean(misspell, corrections)

    str = "Did you mean:\n"

    if corrections.any?{ |i| i.length == misspell.length }
      corrections.select{ |i| i.length == misspell.length }.each{ |i| str << "#{i}\n" }
      return str
    elsif misspell.length > corrections.map(&:length).max
      corrections.map{ |i| Regexp.new(i.split("").join(".*")) }.select{ |r| misspell.match(r) }.each{ |i| str << "#{i}\n" }
    end

    ""

  end

end
