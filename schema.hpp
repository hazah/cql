#include "terminals.hpp"

struct schema {
	// Some global configuration for handling table access
	struct table_config {};
	
	// Tables
	table<table_config> people = {{{"people"}}};
	table<table_config> posts = {{{"posts"}}};
	table<table_config> comments = {{{"comments"}}};

	// Some global configuration for handling column data
	struct col_config {};

	// Columns
	column<col_config> id = {{{"id"}}};
	column<col_config> name = {{{"name"}}};
	column<col_config> title = {{{"title"}}};
	column<col_config> content = {{{"content"}}};

	// Foreign keys
	belongs_to<col_config>	author = {{{"author"}}};
	belongs_to<col_config>	post = {{{"post"}}};

	schema() {
		people.define((
				id(serial, not_null, primary_key)
			,	name(string_, not_null)

			//	has_many
			,	posts
			,	comments
		));

		posts.define((
				id(serial, not_null, primary_key)
			,	title(string_, not_null)
			,	content(text_, not_null)
			
			//	belongs_to
			,	author(id, not_null)

			//	has_many
			,	comments
		));

		comments.define((
				id(serial, not_null, primary_key)
			, 	content(text_, not_null)
			
			//	belongs_to
			, 	post(id, not_null)
			, 	author(id, not_null)
		));
	}
};
