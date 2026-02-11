# MockLib

## About the MockLib

It is an exercise project aimed to hone my C++ coding
skills, after OilCompiler. This is also for me learning
about the C++ library `chrono`, so do not expect much of
a clean chrono usability.

## Goals for me

- [x] Touch on chrono
- [x] Get better at C++
- [x] Do mistakes
- [ ] Get cracked dot io
- [ ] Impress my friends

## Tests done

I have made tests for it in the program itself.

The tests are Minder test, ScopeGuard test, SmallVec tests,
and the Stopwatch tests.

Minder tests itself by setting alarms and advancing.
It's expected output should be:

```none
...
DING!
DING!
...
DING!
...
...
...
DING!
...
```

ScopeGuard is done at the end of the program.
So if the program says the secret message at the program end,
it means it.

SmallVec tests are simple. Since this is just a small test for
mock libraries, I'll only test it's functionality.

It does this conceptually:

```none
push to vector thrice
pop (removes the last element)
then read the two elements
```

The expected output should be:

```none
[0] -> 19
[1] -> 42
```

The brackets are array ID's.

And finally the Stopwatch tests.
It's a bit too much compared to the other tests.
Probably because I'm testing my own learning code.
Though it does two tests.

One tests it's states and time accuracy, and also
tests it's pause and resume capability.

It's expected output should be:

```none
1-2s
Clock is STOPPED.
Clock is RUNNING.
0-1s
1s
```

And one that tests out it's known unintended behavior
A double stop/start.

It's expected output should be:

```none
Stop tests: STOPPED STOPPED
Start tests: RUNNING RUNNING
```

Then the ScopeGuard secret message :3

```none
I <3 u!
```

## Review

It was really fun doing these.
It was fun learning chrono.
Honestly it's like me learning Rust again.
Getting stuck and eventually Getting over it™
It's what I love about doing these, it's just there
are constant problems we can solve, in contrast to
life. Maybe, once in a while, reconsider your problems.
You might never know what's bugging you.

But in all seriousness, it was fun making this.
