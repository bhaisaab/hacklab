#!/usr/bin/env escript
-export([main/1]).
main([X]) ->
    J = list_to_integer(X),
    N = fac(J),
    io:format("factorial ~w = ~w~n", [J,N]).

fac(0) -> 1;
fac(N) -> 
    N * fac(N-1).
