{ pkgs, customPonysay }:
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
		#ponysay # BROKEN
		# Fix for this issue: https://github.com/erkin/ponysay/issues/314
		(ponysay.overrideAttrs {
			src = customPonysay;
		})
	];
}
