{
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs";
		customPonysay = {
			url = "github:Tonyl314/ponysay";
			flake = false;
		};
	};

	outputs =
	{ nixpkgs, customPonysay, self }:
	let
		pkgs = nixpkgs.legacyPackages.x86_64-linux;
		libs = import ./nix/libs.nix { inherit pkgs customPonysay; };
	in
	{
		devShells.x86_64-linux.default = (import ./nix/shell.nix) { inherit pkgs libs;  };
		apps.x86_64-linux.default = (import ./nix/app.nix) { inherit pkgs libs; };
	};
}
