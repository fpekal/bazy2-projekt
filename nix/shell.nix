{ pkgs }:
let
	libs = import ./libs.nix { inherit pkgs; };
in
pkgs.mkShell {
	nativeBuildInputs = libs.nativeBuildInputs;
}
