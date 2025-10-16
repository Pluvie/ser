import json

with open("exe/perf.json") as file:
  data = json.loads(file.read())

coordinates = data['coordinates']
result = { 'x': 0, 'y': 0, 'z': 0 }

for coordinate in coordinates:
  result['x'] += coordinate['x']
  result['y'] += coordinate['y']
  result['z'] += coordinate['z']

result['x'] = result['x'] / len(coordinates)
result['y'] = result['y'] / len(coordinates)
result['z'] = result['z'] / len(coordinates)

if (result['x'] >= -4.99e-30 or result['x'] <= -5.01e-30):
  raise "bad x number parsing"
if (result['y'] <= 4.99e+30 or result['y'] >= 5.01e+30):
  raise "bad y number parsing"
if (result['z'] <= 0.499 or result['z'] >= 0.501):
  raise "bad z number parsing"

#print(result)
