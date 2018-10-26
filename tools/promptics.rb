json = []

loop do

  lecture = {}
  print "Title? "; lecture["title"] = gets.chomp.upcase
  print "Lecturer? "; lecture["lecturer"] = gets.chomp.upcase
  print "Start? "; lecture["start"] = Time.new(*gets.chomp.split.map(&:to_i)).to_i
  print "End? "; lecture["end"] = Time.new(*gets.chomp.split.map(&:to_i)).to_i

  json << lecture

  print "Continue?[Y/n]"; c = gets.chomp; c.match(/n/i)&&break

end

json.each do |lec|
  File.open("timetable.sched", ?w) do |table|
    table << ((lec["start"]>>0)%256).chr << ((lec["start"]>>8)%256).chr << ((lec["start"]>>16)%256).chr << ((lec["start"]>>24)%256).chr
    table << ((lec["end"]>>0)%256).chr << ((lec["end"]>>8)%256).chr << ((lec["end"]>>16)%256).chr << ((lec["end"]>>24)%256).chr
    table << lec["title"][0,42] << 0.chr*(42-lec["title"].length)
    table << lec["lecturer"][0,54] << 0.chr*(54-lec["lecturer"].length)
    table << 0.chr*8 # TODO room
  end
end
