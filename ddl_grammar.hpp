struct cql_ddl_grammar;

struct cql_ddl_grammar_cases {
	template<typename Tag>
	struct case_ : proto::when<
		proto::_,
		fusion::cons<proto::_value, proto::_state>(
			proto::_value, proto::_state
		)
	> {};
};


template<>
struct cql_ddl_grammar_cases::case_<proto::tag::comma>:
	proto::when<
		proto::comma<cql_ddl_grammar, cql_ddl_grammar>,
		cql_ddl_grammar(
				proto::_left
			,	cql_ddl_grammar(proto::_right)
		)
	> {};

struct cql_ddl_grammar:
	proto::switch_<cql_ddl_grammar_cases> {};

