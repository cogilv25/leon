# leon
A C library / dev-env inspired in part by a combination of philosophies from Sean Barret, Casey Muratori, Jonathan Blow among others.

## Current State
Currently there is a linked list abstract data type and I am working on a tree and dynamic array, then I will be implementing file loading with win32 using these and adding other things as I see fit

## Vision
I will be brief for now as I haven't completley pinned it down.. but in essence the idea is to have an integrated development environment based around the concept of an interactive c terminal and an accompanying library that addresses some of the shortcomings of the C language as compared to some "modern" languages. The heart of this is being able to arbitrarily load, compile and execute C code at runtime that is able to access the current state of the terminal/ide as well as hot reloading individual functions.