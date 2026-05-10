# 📝 AbregeFeur

*Abrège quoi ? Abrège feur.*

AbregeFeur is yet another application used for taking notes. Typically here, it
is made taking for notes during lectures. Once you are done with your notes,
you may use any backend LLM of your choice to synthesize them in a clean format
which will be suitable for your revisions. All you gotta do is focus on taking
all the notes you need, and AbregeFeur will handle the task of cleaning and
formatting them.

For now, the application is only a prototype, and there is still much that is
yet to be implemented. Also, I mostly wrote it for myself and will improve it
based on what I need. However, other folks (like you!) may check it out and
use it as well, should it be able to help out in your studies or your work !

## Usage

Once you have installed the package (see below), you will have accessed to 3
artifacts :

- `abregefeur`, this is the application and mostly what you will be looking for
- `libai`, a library used by the project to perform queries to numerous AI
  backends (OpenAI...) while abstracting the trickier C++ parts (HTTP requests,
  API calls...)
- `liborm`, a custom lighweight ORM library to make manipulating and saving
  application data structures to the local SQLite database a little less
  painful.

You can use the independant librairies (`libai` and `liborm`) in your personal
projects in any way you like (make sure to respect the license though). Check
out the header files in `libs/libai/include` and `libs/liborm/include` to see
what is available.

You have two ways to run the application :

- Using your favorite desktop launcher (for example rofi...)
- From the terminal, using the `abrgefeur` command

```sh
abregefeur
```

For now, you might need to specify an API key to access synthesization
features. For now, only OpenAI is supported, for which you may specify a key
by setting it as an environment variable :

```sh
OPENAI_API_KEY="..." abregefeur
```

AbregeFeur relies on a local SQLite database to save persistant data, like
your notes and information about the artifacts you create from them. As of now,
it will be created at the root of the folder from which you run the program.
Be sure to keep this in mind if you are running the application.

## Installation

### Nix

For now, the best way to use it without any headache is to use the Nix package
of the project:

You can add it to a profile like this,  using the project's Nix flake:

```sh
nix profile add github:mccreemainwoody/abregefeur
```

You can also test it out before installing it, using a Nix shell :

```sh
nix shell -p github:mccreemainwoody/abregefeur
```

Finally, you can also add the project inside a NixOS configuration :

```nix
# In your flake.nix
{
  description = "...";

  inputs = {
    # ...
    nixpkgs.url = "...";
    abregefeur = {
      url = "github:mccreemainwoody/abregefeur";
      nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    abregefeur,
    ...
  } @ inputs: let
    system = "...";
  in {
    nixosConfigurations = {
      myConfig = nixpkgs.lib.nixosSystem {
        inherit system;
        specialArgs = {inherit inputs system;};
        modules = [
          ./configuration.nix
          # ...
        ];
      };
    };
  };
}
```

```nix
# In your configuration.nix
# Considering inputs and system are what you have defined as specialArgs
{
  pkgs,
  inputs,
  system,
  ...
}: let
  inherit (inputs) abregefeur;
in {
  # ... (the rest of your config)

  nixpkgs.overlays = [
    (
      final: prev: {
        abregefeur = abregefeur.packages.${system}.default;
      }
    )
  ];

  environment.systemPackages = with pkgs; [
    abregefeur
  ];
}
```

### Build from source

As the project is built using CMake, make sure you have the right dependencies
first :

- Any C++ compiler of your liking. Make sure your compiler
  [supports C++26](https://en.cppreference.com/cpp/26#Compiler_support).
- CMake, version >=3.25
- Qt (Qt Core and Qt Quick), version >=6.10
- CURL, version >=8.19
- [nlohmann_json](https://github.com/nlohmann/json), version >=3.12

You may then install the project using your regular CMake installation
routine :

```sh
cmake -S . -B build
cmake --build build/
cmake --install build/
```

When installing from source, you may use the custom CMake options (and set
them using the `-D` flag) :

- `ABREGEFEUR_USE_STATIC_LIBS`: Compile all libraries as static instead of
  shared. Equivalent of setting both `LIBAI_USE_STATIC_LIBS` and
  `LIBORM_USE_STATIC_LIBS` to `ON`.
- `ABREGEFEUR_ENABLE_QT_DEPLOY`: Install the Qt runtime along with the artifacts
  (this is unecessary if you are installing from source. You can ignore this
  most of the time)
- `LIBAI_USE_STATIC_LIBS`: Compile libai as static instead of shared.
- `LIBORM_USE_STATIC_LIBS`: Compile liborm as static instead of shared.

## License

This project is licensed using the GNU General Public License v3. Make sure to
read it at [LICENSE](LICENSE) for more information about what you are allowed
and not allowed to do with this project.

## Disclaimers

- While conception, and a great part of implementation thinking and writing
  was made by a good old human developer, some parts of the project was written
  with the assistance of an artificial intelligence. Typically, it is mostly
  used in this project to help out with the parts I'm less knowledgeable, like
  how to work inside the Qt environment and the other external libraries the
  project relies on.
