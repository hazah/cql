#include "schema.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(int, const char*[]) {
	string sql;
	schema s;

	table<schema::table_config>& posts = s.posts;
	column<schema::col_config>& id = s.id;

	// SELECT posts.*
	// FROM posts
	// WHERE posts.id = 1

	sql = posts[id == _1];
	cout << sql << endl;

	// SELECT posts.title, posts.content
	// FROM posts
	// WHERE posts.id = 1

	// sql = posts(title, content)[id == _1](1);
	// cout << sql << endl;

	// SELECT posts.title, posts.content, people.name
	// FROM posts
	// JOIN people ON people.id = posts.author_id
	// WHERE author_id = 1

	// sql = posts(title, content, author[name])[author == _1](1);
	// cout << sql << endl;

	// SELECT posts.*, people.name
	// FROM posts
	// JOIN people ON people.id = posts.author_id
	// WHERE author_id = 1

	// posts(posts, author[name])[author == _1](1);

	// SELECT posts.*
	// FROM posts
	// JOIN people ON people.id = posts.author_id
	// WHERE people.id = 1

	// posts[people[id == _1]](1);

	// SELECT posts.*
	// FROM posts
	// (INNER|LEFT|RIGHT) JOIN people ON people.id = posts.author_id
	// WHERE people.id = 1

	// posts[inner[people[id == _1]]](1);
	// posts[left[people[id == _1]]](1);
	// posts[right[people[id == _1]]](1);

	// SELECT comments.*
	// FROM comments
	// JOIN posts ON posts.id = comments.post_id
	// JOIN people ON people.id = posts.author_id
	// WHERE people.id = 1

	// comments[posts[people[id == _1]]](1);
	
	// SELECT comments.*
	// FROM comments
	// JOIN posts ON posts.id = comments.post_id
	// WHERE post.author_id = 1 OR comments.author_id = 1

	// comments[author == _1 || posts[author == _1]](1);

	// SELECT comments.*
	// FROM comments
	// JOIN posts ON posts.id = comments.post_id
	// JOIN people posts_people ON posts_people.id = posts.author_id
	// JOIN people ON people.id = comments.author_id
	// WHERE posts_people.id = 1 AND people.id = 2 

	// comments[posts[people[id == _1]] && people[id == _2]](1, 2);

	// SELECT comments.*
	// FROM comments
	// JOIN posts ON posts.author_id = comments.author_id
	// JOIN people ON people.id = posts.author_id
	// WHERE people.id = 1

	// comments[posts(author == comments[author])[people[id == _1]]](1);

	// SELECT comments.*
	// FROM comments
	// WHERE comments.author_id = 1
	// UNION
	// SELECT comments.*
	// FROM comments
	// WHERE comments.post_id = 2

	// (comments[author == _1] && comments[post == _2])(1, 2);
}