## API

Instant Code Search defines the following HTTP endpoints. All of them
return JSON.

- `/healthcheck`
Returns `{"success": "true"}` if all the nodes are up and ready to receive
requests.

- `/index?path=PATH`
Takes a path on the filesystem and indexes it

- `/isIndexed`
Returns `{"success": "true"}` if all the nodes have indexed paths, and are
ready to receive queries

- `/?q=QUERY`
Returns any file and line number in the indexed path. The response is of
this form:

`{"success": true, "results": ["path/to/file1:5", "path/to/another/file:33", ...]}`

All of these endpoints have been implemented, but we could use your expertise
in making the query endpoint a <em>lot</em> faster.

##  Usage
Before you get started, the first thing to do is to run `build.sh`. This will
grab any related dependencies, and assemble a JAR that the harness will use to
run your code.

To start a specific server, run `bin/start-server`. This looks to see if
your jar is assembled; if it is, it runs the jar, and if not, uses sbt[1].

To start all of your nodes, run `bin/start-servers`. This will start a
master search node, and three search nodes. The master node is the only
node that we communicate with.

The master node runs on port `9090` (and the search nodes on `9091`, `9092`, and
`9093`). Once the servers are up, you can point your browser at
`http://localhost:9090` to communicate with (and query) the master node.

As always, to submit your code, first commit, and then run `git push`.

You can test your code locally via `test/harness`. You can use the
harness to download the test cases we run your code against.

Note that the input is generated randomly on a seed; we'll always run
against the same dictionary (the harness will download that dictionary for
you if you don't have it).

## Constraints

We're limiting the amount of memory that each of your nodes gets to 500mb.

When running your solution, we'll give you up to 4 minutes to index,
after which, ready or not, we'll start sending queries your way!

(We'll be polling `/isIndexed` in the meanwhile, and if at any point, you're
ready to start accepting queries, we'll start sending them.)

## Scoring

The scoring in this level is based on a single metric: the average request
latency over 50 requests. Your score is a function of the ratio of your
average response time to the default solution.

Note that your solution should support substring searches: for example, your
result should contain all lines containing the word "incipiently" to a query
for "incipient".

To beat the level, you will have to perform 4 times as fast as the default
solution in this repository.

## FAQ


- I get this error when compiling the default code:

    `package java.nio.file does not exist`

  What should I do?

  `java.nio.file` has a Java 7 dependency. You can install Java 7 from here[2]
  or with `apt-get install -y openjdk-7-jre openjdk-7-jdk` (on Linux).

- I want to update how the servers start up. Which file should I edit?
  `bin/start-servers`? `bin/start-server`?

  You can run `bin/local-start-servers by hand to start your servers. However,
  on the server, we'll actually run bin/start-server directly to boot your nodes.
  So if you'd like to change how your servers are started, you should modify
  bin/start-server; there shouldn't be any need to change bin/local-start-servers

- The scoring section above states that scoring depends purely on request latency.
  Does this mean that I can return arbitrary responses really fast?

  Sadly, no. Correctness is a prerequisite for scoring.

Good luck!

[1] http://scala-sbt.org

[2] http://www.oracle.com/technetwork/java/javase/downloads/jdk7-downloads-1880260.html

[3] http://en.wikipedia.org/wiki/LXC
