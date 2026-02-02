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
  / Fiche réelle :
]

#table(
  columns: 6,
  table.header([Acteur], [Tâches], [Début], [Fin prévue], [Fin réelle], [Commentaires]),
  [Paul Maget], [Établir le modèle d'architecture], [27/01], [03/02], [--/--], [...],
  [Paul Maget], [Faire le widgets d'affichage des photos sur la vue galerie], [27/01], [03/02], [--/--], [...],
  [Khadija Ammari], [Faire la toolbar de la vue galerie], [27/01], [03/02], [01/03], [Perpective d'amélioration : implémenter un meilleur style.],
  [Valentin Mary], [Créer la vue galerie vide], [27/01], [03/02], [01/02], [Le conteneur permettant l'existence de la toolbar et la grille de photos est créé.],
  [Valentin Mary], [Écrire le modèle des métadonnées des images], [27/01], [03/02], [02/02], [Un modèle simple est disponible, avec l'emplacement et les propriétés basiques des photos (noms, taille, ...).],
  [Sokhna Diop], [Faire la vue inspecteur], [27/01], [03/02], [--/--], [...],
  [Vanessa Qufaj], [Écrire un modèle/programme permettant de deserialiser les métadonnées existantes des images ], [27/01], [03/02], [01/02], [Un programme d'extraction des métadonnées pour des fichier jpg et png existe, il faudra encore l'étendre et l'améliorer lors de la prochaine itération.],
  [Khadija Ammari], [Faire le programme de recherche/indexage des images], [27/01], [03/02], [01/02], [Une classe dédié à cette tâche a été créé et filtre les fichiers .jpeg, .jpg et .png],
  [Sokhna Diop], [Créer la splitview de l'écran pincipal], [27/01], [03/02], [--/--], [...],
  [Sokhna Diop], [Conception de l'interface avec figma], [27/01], [03/02], [03/02], [Cette tâche sera prolongée lors de la prochaine itération afin de poursuivre la conception graphique des prochaines fonctionnalités.], 
)
