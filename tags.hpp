#include <string>

using std::string;

template<typename T>
struct type_ : T {};

template<>
struct type_<int> {};

struct not_null_ {};
struct primary_key_ {};
struct serial_ {};

template<typename I>
struct placeholder_ : I, string { using string::string; };

struct join_ : string { using string::string; };

struct table_ : string { using string::string; };
struct column_ : string { using string::string; };
struct belongs_to_ : string { using string::string; };