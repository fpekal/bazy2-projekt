{ pkgs, customPonysay }:
{
	nativeBuildInputs =
	with pkgs; [
		pkg-config
		gcc
		gnumake
	];

	buildInputs =
	with pkgs; [
		sqlite.dev

		#ponysay # BROKEN
		# Fix for this issue: https://github.com/erkin/ponysay/issues/314
		(ponysay.overrideAttrs {
			src = customPonysay;
		})
	];
}
