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
#subtitle[Fiche d'itération n°4 du 18/02/2026 au 21/02/2026]

Objectifs :
- Finir la vue principale
- Permettre le rognage depuis l'interface
- Améliorer l'accessibilité
- Charger les images plus rapidement

Tâches à réaliser :
+ Relier les logiques à l'UI
+ Créer des actions clavier
+ Revoir les algorithmes de chargement des images
+ Finir les tâches non terminées de l'itération précédente

Documentation :
- Document d'architecture: #link("https://github.com/Vrock691/IHM/wiki/Archi")

#align(center)[
  / Fiche réelle :
]

#table(
  columns: 6,
  table.header([Acteur], [Tâches], [Début], [Fin prévue], [Fin réelle], [Commentaires]),
  [Sokhna], [Implémenter l'empty state de la sidebar], [11/02], [21/02], [20/02], [],
  [Sokhna], [Créer les ressentis et les relier au sélécteur dans l'UI inspecteur], [11/02], [21/02], [19/02], [],
  [Vanessa], [Ajouter déserialisation et union des imageModels dans le constructeur de GalleryView], [11/02], [21/02], [20/02], [],
  [Paul], [Implémenter GalleryView.setSelected], [11/02], [21/02], [18/02], [],
  [Sokhna], [Enlever les dropdown de GalleryView], [11/02], [21/02], [18/02], [],
  [Vanessa], [Créer l'UI de la sidebar en Empty State sur Figma], [11/02], [21/02], [18/02], [],
  [Vanessa], [Gérer les mises à jour du modele de l'onglet depuis la sidebar], [11/02], [21/02], [20/02], [],
  [Khadija], [Faire l'UI de ImageViewer], [11/02], [21/02], [20/02], [Utilise ImageRenderer pour le rendu de l'image centrale.],
  [Paul], [Implémenter Gallery.
  onRequestSetCurrentTab], [11/02], [21/02], [19/02], [],
  [Paul], [Implémenter Gallery.setCurrentTab], [11/02], [21/02], [20/02], [],
  [Vanessa], [Récupérer les informations des images], [11/02], [21/02], [18/02], [],
  [Valentin], [Remanier la vue Gallery], [18/02], [21/02], [19/02], [],
  [Paul], [Corriger beug sur la séléction d'onglet], [18/02], [21/02], [20/02], [],
  [Sokhna], [Donner un style à l'image selectionné], [18/02], [21/02], [--/--], [Abandonné],
  [Valentin], [Faire la navigation au clavier], [18/02], [21/02], [--/--], [Abandonné],
  [Paul], [Gérer les mises à jour du modèle des images depuis l'inspecteur], [18/02], [21/02], [20/02], [],
  [Khadija], [Corriger beug pas de scroll dans GalleryView], [18/02], [21/02], [19/02], [],
  )