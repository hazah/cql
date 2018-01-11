template<typename Grammar>
struct _compare : proto::transform<_compare<Grammar>>
{
    template<typename Expr, typename State, typename Data>
    struct impl : proto::transform_impl<Expr, State, Data>
    {
        typedef
            string
        result_type;

        result_type operator ()(
            typename impl::expr_param expr
          , typename impl::state_param state
          , typename impl::data_param data
        ) const
        {
        	return 	Grammar()(proto::left(expr), state) + " = " + 
        			Grammar()(proto::right(expr), state);
        }
    };
};

struct _column : proto::transform<_column>
{
    template<typename Expr, typename State, typename Data>
    struct impl : proto::transform_impl<Expr, State, Data>
    {
        typedef
            string
        result_type;

        result_type operator ()(
            typename impl::expr_param expr
          , typename impl::state_param state
          , typename impl::data_param data
        ) const
        {
        	string result = proto::value(expr);
        	
        	if (state.size() > 0) {
        		result = state + "." + result;
        	}

        	return result;
        }
    };
};

namespace boost{ namespace proto {

template<typename G>
struct is_callable<_compare<G>>
  : mpl::true_
{};

template<>
struct is_callable<_column>
  : mpl::true_
{};

}}

struct cql_sql_grammar;

struct cql_sql_grammar_cases {
	template<typename Tag>
	struct case_ : proto::not_<proto::_> {};
};


template<>
struct cql_sql_grammar_cases::case_<proto::tag::terminal>:
	proto::or_<
			proto::when<
					proto::terminal<column_>
				,	_column(proto::_, proto::_state)
			>
		,	proto::when<
					proto::terminal<table_>
				,	proto::_value
			>
		,	proto::when<
					proto::terminal<placeholder_<proto::_>>
				,	proto::_value
			>		
	> {};


template<>
struct cql_sql_grammar_cases::case_<proto::tag::equal_to>:
	proto::when<
			proto::equal_to<cql_sql_grammar, cql_sql_grammar>
		,	_compare<cql_sql_grammar>(proto::_, proto::_state)
	> {};


template<>
struct cql_sql_grammar_cases::case_<proto::tag::subscript>:
	proto::when<
			proto::subscript<proto::terminal<table_>, cql_sql_grammar>
		,	cql_sql_grammar(
					proto::_right
				,	cql_sql_grammar(proto::_left)
			)
	> {};

struct cql_sql_grammar:
	proto::switch_<cql_sql_grammar_cases> {};