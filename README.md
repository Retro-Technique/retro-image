# Retro Image

Retro Image est une bibliothèque C++ minimaliste fournissant des fonctionnalités de manipulation d’images bitmap, conçue pour être simple, portable et extensible.  
Le projet est distribué sous licence CeCILL (compatible avec la GPL), adaptée aux logiciels libres en France.

## Fonctionnalités

- Chargement et sauvegarde d’images bitmap (PNG, JPEG, BMP)
- Manipulation des pixels (masquage, transparence, etc.)
- Opérations sur les images : flip vertical, flip horizontal, etc.
- Interface orientée objet en C++20
- Tests unitaires avec Boost Test

## Prérequis

- Visual Studio 2022 ou GCC (Linux)
- CMake ≥ 3.21
- C++20
- vcpkg (pour la gestion des dépendances)
- Boost (pour les tests unitaires)

## Installation

### Clonage du dépôt

git clone https://github.com/<votre-utilisateur>/<votre-repo>.git cd <votre-repo>

### Construction avec CMake

#### Sous Windows

cmake -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_GENERATOR_PLATFORM=x64 -S . cmake --build build --config Release

#### Sous Linux

cmake -B build -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -S . cmake --build build --config Release

## Utilisation

Incluez les headers nécessaires dans votre projet :

#include <retro/image.h>

Exemple de création et manipulation d’une image :

retro::image::bitmap bmp; 
bmp.create(640, 480); 
bmp.flip_vertical(); 
bmp.save_to_file("output.png");

## Tests

Les tests unitaires sont basés sur Boost Test.  
Pour exécuter les tests :
ctest --build-config Release


## Intégration continue

Le projet utilise GitHub Actions pour la compilation, l’analyse statique (Cppcheck) et l’exécution des tests sur Windows et Linux.

## Licence

Ce projet est sous licence CeCILL.  
Voir le fichier [LICENSE](LICENSE) pour plus d’informations.

---

Pour toute question ou contribution, n’hésitez pas à ouvrir une issue ou une pull request !