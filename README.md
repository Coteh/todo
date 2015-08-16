todo
=========

todo is a simple to-do command line application written in C++.

Todo entries are currently stored as json files and parsed with [RapidJSON](https://github.com/miloyip/rapidjson).

Features
---------
- Add/remove todo entries containing title and description
- Assign todo entries to categories
- Add labels to todo entries
- Check off todo items that have been completed

Issues
---------
- Command parsing logic is messy/spaghettio
  - Todo list is always read at the beginning of the program regardless of command entered

- Report an issue in Issues if you find something not listed here

Future Additions
---------
- Add due dates to todo items and implement reminder functionality
- Add ability to switch between different sets of todo lists (currently the current todo list filepath has to be set within config)
- See more in the [example todo database file.](todo.jsondb) :)
