{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  packages = [
    boost
    cmake
    ninja
  ];
}