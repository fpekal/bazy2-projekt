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
		# Fix for this issue: https://github.com/erkin/ponysay/issues/314
		overlayCustomPonysay = (final: prev: {
			ponysay = prev.ponysay.overrideAttrs { src = customPonysay; };
		});
		pkgs = import nixpkgs { system = "x86_64-linux"; overlays = [overlayCustomPonysay]; };
		libs = import ./nix/libs.nix { inherit pkgs; };
	in
	{
		devShells.x86_64-linux.default = (import ./nix/shell.nix) { inherit pkgs libs;  };
		apps.x86_64-linux.default = (import ./nix/app.nix) { inherit pkgs libs; };
	};
}
