{ pkgs, libs }:
pkgs.mkShell {
	nativeBuildInputs = libs.nativeBuildInputs ++ libs.buildInputs;
}
