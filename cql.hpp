#include "tags.hpp"

#include <boost/proto/proto.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace mpl = boost::mpl;
namespace fusion = boost::fusion;
namespace proto = boost::proto;

using boost::shared_ptr;
using proto::_;
using std::string;

#include "ddl_grammar.hpp"
#include "sql_grammar.hpp"

template<typename Expr>
struct cql;

typedef cql<proto::terminal<type_<int>>::type> const int_type;
typedef cql<proto::terminal<type_<string>>::type> const string_type;
typedef cql<proto::terminal<type_<string>>::type> const text_type;
typedef cql<proto::terminal<not_null_>::type> const not_null_type;
typedef cql<proto::terminal<primary_key_>::type> const primary_key_type;
typedef cql<proto::terminal<serial_>::type> const serial_type;

typedef cql<proto::terminal<placeholder_<mpl::int_<0>>>::type> const _1_type;
typedef cql<proto::terminal<placeholder_<mpl::int_<1>>>::type> const _2_type;

typedef cql<proto::terminal<join_>::type> inner_join_type;
typedef cql<proto::terminal<join_>::type> left_join_type;
typedef cql<proto::terminal<join_>::type> right_join_type;

struct cql_domain: proto::domain<proto::pod_generator<cql>> {};

// Column definition
template<typename Configuration, typename Dummy = proto::is_proto_expr>
struct column_base {
	BOOST_PROTO_EXTENDS(proto::terminal<column_>::type, column_base<Configuration>, cql_domain)
};

// Foreign key definition
template<typename Configuration, typename Dummy = proto::is_proto_expr>
struct belongs_to_base {
	BOOST_PROTO_EXTENDS(proto::terminal<belongs_to_>::type, belongs_to_base<Configuration>, cql_domain)
};

// Table definition
struct table_def {};

template<typename Def>
struct table_def_impl: table_def {
	Def def;

	typedef void row_type;

	table_def_impl(const Def& def): def(def) {}
};

template<typename Configuration, typename Dummy = proto::is_proto_expr>
struct table_base {
	BOOST_PROTO_EXTENDS(proto::terminal<table_>::type, table_base<Configuration>, cql_domain)

	template<typename Def>
	void define(Def def) {
		definition = shared_ptr<table_def>(new table_def_impl<Def>(def));
	}
	shared_ptr<table_def> definition;
};

template<typename Configuration>
using table = cql<table_base<Configuration>>;

template<typename Configuration>
using column = cql<column_base<Configuration>>;

template<typename Configuration>
using belongs_to = cql<belongs_to_base<Configuration>>;

template<typename Expr>
struct cql {
    BOOST_PROTO_EXTENDS(Expr, cql, cql_domain)

    typedef string result_type;

    operator string() const {
		BOOST_MPL_ASSERT((proto::matches<Expr, cql_sql_grammar>));
		
		cql_sql_grammar grammar;
    	return grammar(*this);
    }

    template<typename Def>
    void define(Def def) {
    	BOOST_MPL_ASSERT((proto::matches<Expr, proto::terminal<table_>>));

    	proto_expr_.define(def);
    }
};
