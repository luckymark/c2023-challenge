{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  packages = [
    boost
    ncurses
    cmake
    ninja
    pkg-config
  ];
}