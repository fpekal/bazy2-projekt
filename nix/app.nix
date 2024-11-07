{ pkgs }:
let
	libs = import ./libs.nix { inherit pkgs; };

	package =
	pkgs.stdenv.mkDerivation {
		name = "pony";
		version = "0.0.1";

		nativeBuildInputs = libs.nativeBuildInputs;
		buildInputs = libs.buildInputs;

		src = ./..;
	};
in
{
	type = "app";
	program = "${package}/bin/pony";
}
