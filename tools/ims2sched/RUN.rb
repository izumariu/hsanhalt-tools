#!/usr/bin/env ruby

require "time"
require "yaml"
require "#{File.dirname(__FILE__)}/libuniics.rb"

HOUR = 60*60
CLASSES = %w(FSL1 FSL3 FSL5 FSL7 IMS1Ü1 IMS1Ü2 IMS3Ü1 IMS3Ü2 IMS5 IMS7 MIM2 MS L2 MIAM2)
PROFS = YAML.load open("#{File.dirname(__FILE__)}/lecturers.yaml", &:read)
SUMMARY_REGEX = Regexp.new("(#{CLASSES.join(?|)})(\\s+#{CLASSES.join("|\\s+")})*\s+(#{PROFS.keys.join(?|)})")
DAYS = %w(Sunday Monday Tuesday Wednesday Thursday Friday Saturday)

if ARGV.length != 2
  abort "USAGE: #{__FILE__.split(?/)[-1]} <ICS FILE> <P_GROUP_NUM>"
end

file, pgroup = ARGV

pgroup = pgroup.to_i

unless [1,2].include?(pgroup)
  abort "E: P_GROUP_NUM must be either 1 or 2\n(Tip: If you're in Ü2, group 3 becomes 1 and group 4 becomes 2)"
end

cal = HSAnhaltICS.from(file, PROFS)

cal.schedule.each do |group|
  if group.length == 1
    lec = group.first
  else
    lec = group[pgroup - 1]
  end
  puts "#{lec.title||"<unknown>"}"
  puts "- by #{lec.lecturer||"<unknown>"}"
  puts "- starts #{DAYS[Time.at(lec.start).wday]}, #{Time.at(lec.start)}"
  puts "- ends   #{DAYS[Time.at(lec.start).wday]}, #{Time.at(lec.end)}"
  puts "- in room #{lec.location||"<unknown>"}"
  puts
end
