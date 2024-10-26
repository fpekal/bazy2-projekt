{
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs";
	};

	outputs =
	{ nixpkgs, self }:
	let
		pkgs = nixpkgs.legacyPackages.x86_64-linux;
	in
	{
		devShells.x86_64-linux.default = (import ./nix/shell.nix) { inherit pkgs; };
	};
}
