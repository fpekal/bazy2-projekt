{ pkgs }:
{
	nativeBuildInputs =
	with pkgs; [
		pkg-config
		gcc14
		gnumake
	];

	buildInputs =
	with pkgs; [
		ponysay
		sqlite.dev
		boost.dev
	];
}
