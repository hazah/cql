#include "cql.hpp"
// Generic terminals
// Types
int_type 		int_ = {{}};
string_type 	string_ = {{}};
text_type 		text_ = {{}};

// Modifiers
not_null_type 		not_null = {{}};
primary_key_type 	primary_key = {{}};
serial_type 		serial = {{}};

// Placeholders
_1_type _1 = {{{"_1"}}};
_2_type _2 = {{{"_2"}}};

// Join types
inner_join_type inner = {{{"INNER JOIN"}}};
left_join_type left = {{{"LEFT OUTER JOIN"}}};
right_join_type right = {{{"RIGHT OUTER JOIN"}}};
