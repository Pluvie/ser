package main

import (
	"encoding/json"
	"errors"
	//"fmt"
	"os"
)

type Coordinate struct {
	X, Y, Z float64
}

type CoordinatesData struct {
	Coordinates []Coordinate
}

func (d CoordinatesData) Average() Coordinate {
	var coord Coordinate
	for i := range d.Coordinates {
		coord.X += d.Coordinates[i].X
		coord.Y += d.Coordinates[i].Y
		coord.Z += d.Coordinates[i].Z
	}
	count := float64(len(d.Coordinates))
	coord.X /= count
	coord.Y /= count
	coord.Z /= count
	return coord
}

func run() error {
	var result Coordinate
	var data CoordinatesData

	bytes, err := os.ReadFile("exe/perf.json")
	if err != nil {
		return err
	}

	err = json.Unmarshal(bytes, &data)
	if err != nil {
		return err
	}

	result = data.Average()
	//fmt.Printf("%+v\n", result);
	err = verify(result)
	if err != nil {
		return err
	}

	return nil
}

func verify(result Coordinate) error {
	if (result.X >= -4.99e-30 || result.X <= -5.01e-30) {
		return errors.New("bad X number parsing")
	}

	if (result.Y <= 4.99e+30 || result.Y >= 5.01e+30) {
		return errors.New("bad Y number parsing")
	}

	if (result.Z <= 0.499 || result.Z >= 0.501) {
		return errors.New("bad Z number parsing")
	}

	return nil
}

func main() {
	err := run()
	if err != nil {
		panic(err)
	}
}
