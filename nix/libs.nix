{ pkgs }:
{
	nativeBuildInputs =
	with pkgs; [
		sqlite.dev

		pkg-config
		gcc
		gnumake
	];

	buildInputs =
	with pkgs; [
		sqlite
	];
}
