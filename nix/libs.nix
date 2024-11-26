{ pkgs }:
{
	nativeBuildInputs =
	with pkgs; [
		pkg-config
		gcc
		gnumake
	];

	buildInputs =
	with pkgs; [
		ponysay
		sqlite.dev
	];
}
