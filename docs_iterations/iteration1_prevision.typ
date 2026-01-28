// LTeX: language=fr

#set text(font: "FreeSans")
#set page(header: [
  Paul Maget,
  Khadija Ammari,
  Valentin Mary#h(1fr) Projets IHM -- 2025-2026 - Groupe 3\
  Vanessa Qufaj,
  Sokhna Diop
])

#show title: (content) => {
  set text(size: 1.5em, weight: "light")
  align(center)[#content]
}

#let subtitle(content) = {
  set text(size: 2em, weight: "light", fill: color.blue)
  set align(center)
  content
}

#title[Gestion d’une bibliothèque de photos]
#subtitle[Fiche d'itération n°1 du 27/01/2026 au 03/02/2026]

Objectifs :
- S'approprier le projet
- Modéliser les données nécessaires
- Construire l'architecture du projet

Tâches à réaliser :
+ Créer la base de l'interface
+ Modéliser les structures de données des images et l'architecture  qui sera utilisée par l'application
+ Produire de la documentation utile pour la suite du projet

#align(center)[
  / Fiche prévisionnelle :
]

#table(
  columns: 6,
  table.header([Acteur], [Tâches], [Début], [Fin prévue], [Fin réelle], [Commentaires]),
  [Paul Maget], [Établir le modèle d'architecture], [27/01], [03/02], [], [Établir l'achitecture et le modèle des différentes classes de l'application.],
  [Paul Maget], [Faire le widgets d'affichage des photos sur la vue galerie], [27/01], [03/02], [], [Définir la grille des photos, et les diffèrents widgets qui en découlent],
  [Khadija Ammari], [Faire la toolbar de la vue galerie], [27/01], [03/02], [], [],
  [Valentin Mary], [Créer la vue galerie vide], [27/01], [03/02], [], [Créer un conteneur permettant l'existence de la toolbar et la grille de photos],
  [Valentin Mary], [Créer la vue galerie vide], [27/01], [03/02], [], [Créer un conteneur permettant l'existence de la toolbar et la grille de photos],
  [Valentin Mary], [Écrire le modèle des métadonnées des images], [27/01], [03/02], [], [Créer un modèle incluant les métadonnées existantes de l'image + commencer implémenter des métadonnées spécifiques à notre logiciel],
  [Sokhna Diop], [Faire la vue inspecteur], [27/01], [03/02], [], [Créer le widget de la vue inspecteur et quelques propriétés basiques (cf #10 #7)],
  [Vanessa Qufaj], [Écrire un modèle/programme permettant de deserialiser les métadonnées existantes des images ], [27/01], [03/02], [], [Faire une recherche de l'état de l'art des différentes propriétés sérialisable de png, jpeg, etc
  Si possible écrire un programme pour traiter ces opérations.

  Par exemple :

  taille du fichier
  taille de l'image en pixel
  ...],
  [Khadija Ammari], [Faire le programme de recherche/indexage des images], [27/01], [03/02], [], [Programme de recherche/indexation des images dans un dossier donné.
  Créer une classe IndexationService()],
  [Sokhna Diop], [Créer la splitview de l'écran pincipal], [27/01], [03/02], [], [Créer la splitview de l'écran pincipal permettant le redimensionnement des vues galerie et inspecteur],
  [Sokhna Diop], [Conception de l'interface avec figma], [27/01], [03/02], [], [], 
)

#align(center)[
  / Fiche réelle :
]

#table(
  columns: 6,
  table.header([Acteur], [Tâches], [Début], [Fin prévue], [Fin réelle], [Commentaires]),
  [], [], [], [], [], [],
)