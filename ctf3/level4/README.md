# SQLCluster

SQLCluster makes your SQLite highly-available.

## Getting started

To run this level, you'll need a working Go installation. If you don't
have one yet, it's quite easy to obtain. Just grab the appropriate
installer from:

  https://code.google.com/p/go/downloads/list

Then set your GOPATH environment variable:

  http://golang.org/doc/code.html#GOPATH

It'll probably be convenient to check this code out into
$GOPATH/src/stripe-ctf.com/sqlcluster (that way, `go build` will know
how to compile it without help). However, you can use the provided
`build.sh` regardless of where you happened to check this level out.

## Building and running

Run `./build.sh` to build the SQLCluster binary.

As always, you can run test cases via `test/harness`. This will
automatically fetch and compile Octopus, download your test cases, and
score your level for you.

Octopus will print out your score, together with how it arrived at
said score.

## Protocol

SQCluster communicates with the outside world over HTTP. The public
interface is simple:

  POST /sql:

    input:  A raw SQL body

    output: A message with the form "SequenceNumber: $n", followed
            by the output of that SQL command.

Run `./build.sh` to build SQLCluster and have it print out some
example usage (including `curl`s you can run locally).

## Supported platforms

SQLCluster has been tested on Mac OSX and Linux. It may work on other
platforms, but we make no promises. If it's not working for you, see
https://stripe-ctf.com/about#development for advice on getting a
development environment similar to our own.

## Scoring

You gain 30 point for each correct query. We then subtract 0.5 *
sqrt(network traffic). Responding incorrectly to a query is a
disqualification (though you can reject a query by returning a non-200
status code).

There is a threadpool per node hammering that node with SQL requests
as quickly as your node can respond. If a request is rejected, it'll
be retried every 100ms against the same node until it succeeds. (See
[1] for the code that implements this.)

The link between Octopus and your nodes is reliable, while the links
between your nodes are not. We'll spawn your nodes once; if they exit
on their own your solution will be disqualified.

[1] https://github.com/stripe-ctf/octopus/blob/master/harness/harness.go#L69-L111
