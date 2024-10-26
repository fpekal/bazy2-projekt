{ pkgs, ... }:
pkgs.mkShell {
	buildInputs = with pkgs; [
		sqlite.dev
		#sqlitecpp

		pkg-config
		gcc
		gnumake
	];
}
