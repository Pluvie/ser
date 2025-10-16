/* The coordinate to parse from JSON. */
struct coordinate {
  dec x;
  dec y;
  dec z;
};


/*
  Defines the containers used for the parsing.
  In this case, a list<struct coordinate>.
*/
#define list_of struct coordinate
#include <ion/containers/list.h>

#define list_function(t, f, ...)                              \
  _Generic(t,                                                 \
    list<struct coordinate> : list<struct coordinate>_ ## f   \
  )

#define list_of struct coordinate
#include <ion/containers/list.c>

/*
  Now that we have the container, we can define the target result of the JSON parsing.
*/
struct coordinates_data {
  list<struct coordinate> coordinates;
};

/*
  Defines the reflections utilized to parse the JSON.
*/
struct reflection coordinate_reflection =
  reflect(struct coordinate, STRUCT, fields(
    field(struct coordinate, DEC, x),
    field(struct coordinate, DEC, y),
    field(struct coordinate, DEC, z),
  )
);

struct reflection coordinates_data_reflection =
  reflect(struct coordinates_data, STRUCT, fields(
    field(struct coordinates_data, LIST, coordinates,
      of(coordinate_reflection), container(list, struct coordinate)),
  )
);

/*
  The function used to parse the JSON and calculate the average coordinate value.
*/
struct coordinate run(
    str* json,
    struct allocator* allocator
);

/*
  The function used to verify the parsing result.
*/
bool verify (
    struct coordinate* result
);
