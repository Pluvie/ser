//use std::fmt::{self, Display, Formatter};
//use std::io::Write;
use std::fs;
use serde::Deserialize;

#[derive(Debug, Deserialize, PartialEq)]
struct Coordinate {
    x: f64,
    y: f64,
    z: f64,
}

/*
impl Display for Coordinate {
    fn fmt(&self, formatter: &mut Formatter<'_>) -> fmt::Result {
        write!(
            formatter,
            "Coordinate {{ x: {:e}, y: {:e}, z: {} }}",
            self.x, self.y, self.z
        )
    }
}
*/

#[derive(Deserialize)]
struct CoordinatesJSON {
    coordinates: Vec<Coordinate>,
}

fn run(s: &str) -> Coordinate {
    let jobj = serde_json::from_str::<CoordinatesJSON>(s).unwrap();

    let len = jobj.coordinates.len() as f64;
    let mut x = 0_f64;
    let mut y = 0_f64;
    let mut z = 0_f64;

    for coord in &jobj.coordinates {
        x += coord.x;
        y += coord.y;
        z += coord.z;
    }

    Coordinate {
        x: x / len,
        y: y / len,
        z: z / len,
    }
}

fn verify(result: &Coordinate) {
  if result.x >= -4.99e-30 || result.x <= -5.01e-30 {
    panic!("bad x number parsing");
  }

	if result.y <= 4.99e+30 || result.y >= 5.01e+30 {
    panic!("bad x number parsing");
  }

	if result.z <= 0.499 || result.z >= 0.501 {
    panic!("bad x number parsing");
  }
}

fn main() {
    let s = fs::read_to_string("exe/perf.json").unwrap_or_default();
    let result = run(&s);
    verify(&result);
    //println!("{result}");
}
