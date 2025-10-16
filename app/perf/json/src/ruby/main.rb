require "json"

data = JSON.parse(File.read("exe/perf.json"))

coordinates = data['coordinates']
result = { 'x' => 0, 'y' => 0, 'z' => 0 }

coordinates.each do |coordinate|
  result['x'] += coordinate['x']
  result['y'] += coordinate['y']
  result['z'] += coordinate['z']
end

result['x'] = result['x'] / coordinates.length
result['y'] = result['y'] / coordinates.length
result['z'] = result['z'] / coordinates.length

if result['x'] >= -4.99e-30 or result['x'] <= -5.01e-30
  raise "bad x number parsing"
end
if result['y'] <= 4.99e+30 or result['y'] >= 5.01e+30
  raise "bad y number parsing"
end
if result['z'] <= 0.499 or result['z'] >= 0.501
  raise "bad z number parsing"
end

#puts result
