// LTeX: language=fr

#set text(font: "FreeSans")
#set page(header: [
  Paul Maget,
  Khadija Ammari,
  Valentin Mary#h(1fr) Projets IHM -- 2025-2026\
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

#show link: text.with(fill: blue)
#show link: underline

#title[Gestion d’une bibliothèque de photos]
#subtitle[Fiche d'itération n°2 du 04/02/2026 au 10/02/2026]

Objectifs :
- Rendre les fonctionnalités basiques de l'application utilisables;
- Améliorer l'interface graphique;
- Implémenter et améliorer les différents algorithmes;

Tâches à réaliser :
+ Continuer l'implémentation de l'architecture et préciser les zones d'ombres;
+ Implémenter les logiques de filtrage/triage de fichiers;
+ Améliorer les modèles de manipulation des différentes données;
+ Permettre le lancement de l'application avec ses services;

Documentation :
- Document d'architecture: #link("https://github.com/Vrock691/IHM/wiki/Archi")

#align(center)[
  / Fiche réelle :
]

#table(
  columns: 6,
  table.header([Acteur], [Tâches], [Début], [Fin prévue], [Fin réelle], [Commentaires]),
  [Sokhna], [Faire la vue inspecteur], [04/02], [10/02], [09/02], [Continuation de la tâche de l'itération 1, avec les incréments du figma pris en compte.],
  [Valentin], [Ajouter SerialisationService], [04/02], [10/02], [05/02], [],
  [Valentin], [Implémenter SerialisationService. serializeImageModel], [04/02], [10/02], [--/--], [Tâche en retard à cause d'une incompréhension de la bibliothèque de Sérialisation Qt.],
  [Khadija], [Améliorer IndexationService], [04/02], [10/02], [08/02], [Algorithme fonctionnel, retourne un vecteur d'ImageModel.],
  [Paul et Vanessa], [Finir ImageModel], [04/02], [10/02], [08/02], [Contenu d'ImageModel défini. Getter et Setter implémentés.],
  [Valentin], [Faire TabModel], [04/02], [10/02], [08/02], [TabModel défini, avec gestion des filtres et tris.],
  [Vanessa], [Implémenter l'initialisation de Gallery], [04/02], [10/02], [09/10], [Méthodes à étendre lors de la prochaine itérations.],
  [Paul], [Implémenter GalleryView. onRequestSelect], [04/02], [10/02], [10/02], [],
  [Sokhna], [Ajouter InspectorView. setSelected()], [04/02], [10/02], [09/02], [Style à améliorer.],
  [Paul], [Implémenter le lancement de l'application], [04/02], [10/02], [10/02], [À étendre avec la nouvelle organisation des onglets dans la prochaine itération.],
  [Sokhna], [Conception de l'interface avec Figma], [04/02], [10/02], [10/02], []
  )