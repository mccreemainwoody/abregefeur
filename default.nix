{
  pkgs,
  system ? pkgs.stdenv.hostPlatform.system,
  platforms ? [system],
  ...
}:
pkgs.stdenv.mkDerivation {
  pname = "abregefeur";
  version = "0.1.0";
  src = ./.;

  meta = {
    inherit platforms;
    decription = "An note synthesizer that uses AI to make better summaries.";
    mainProgram = "abregefeur";
  };

  nativeBuildInputs = with pkgs; [
    cmake
    ninja
    pkg-config
    qt6.wrapQtAppsHook
  ];

  buildInputs = with pkgs; [
    qt6.qtbase
    qt6.qtdeclarative
    curl
    nlohmann_json
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
  ];
}
