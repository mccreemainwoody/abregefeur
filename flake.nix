{
  description = "An note synthesizer that uses AI to make better summaries.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {
        inherit system;
      };
      app = import ./default.nix {
        inherit pkgs system;
        platforms = flake-utils.lib.defaultSystems;
      };
    in {
      formatter = pkgs.alejandra;

      packages = rec {
        default = abregefeur;
        abregefeur = app;
      };
    });
}
