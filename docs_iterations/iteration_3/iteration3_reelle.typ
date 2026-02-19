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
#subtitle[Fiche d'itération n°3 du 11/02/2026 au 17/02/2026]

Objectifs :
- Rendre l'affichage des photos fonctionnel;
- Afficher l'ensemble des ressources des photos;
- Finir le système d'onglet;

Tâches à réaliser :
+ Permettre le lancement de l'application avec ses services;
+ Créer un module de gestion des onglets;
+ Relier les différentes méthodes de sérialisation et d'opération aux composants graphiques;

Documentation :
- Document d'architecture: #link("https://github.com/Vrock691/IHM/wiki/Archi")

#align(center)[
  / Fiche réelle :
]

#table(
  columns: 6,
  table.header([Acteur], [Tâches], [Début], [Fin prévue], [Fin réelle], [Commentaires]),
  [Valentin], [Finir d'implémenter SerialisationService], [04/02], [15/02], [15/02], [],
  [Sokhna], [Implémenter l'empty state de la sidebar], [11/02], [17/02], [--/--], [Mauvais emptyState mis en oeuvre, à modifier d'ici la fin du projet.],
  [Sokhna], [Supprimer l'ancienne vue Galerie de Mainwindow et la replacer par VueGalery], [11/02], [17/02], [17/02], [Implémentation à revoir lors de la prochaine itération.],
  [Paul], [Finir l'affichage des images grâce à ImageCell dans GaleryView], [11/02], [17/02], [17/02], [],
  [Sokhna], [Créer l'UI d'ajout des onglets], [11/02], [17/02], [17/02], [],
  [Khadija], [Créer l'UI de renommage/suppression des onglets], [11/02], [17/02], [17/02], [],
  [Valentin], [Créer un TabManager], [11/02], [17/02], [17/02], [],
  [Paul], [Implémenter Inspector.onModelChanged], [11/02], [17/02], [17/02], [],
  [Sokhna], [Créer les ressentis et les relier au sélécteur dans l'UI inspecteur], [11/02], [17/02], [--/--], [],
  [Paul], [Refaire l'UI des entêtes des onglets], [11/02], [17/02], [17/02], [],
  [Vanessa], [Ajouter déserialisation et union des imageModels dans le constructeur de GalleryView], [11/02], [17/02], [--/--], [],
  [Paul], [Implémenter GalleryView.setSelected], [11/02], [17/02], [--/--], [],
  [Sokhna], [Enlever les dropdown de GalleryView], [11/02], [17/02], [--/--], [],
  [Valentin], [Relier l'ajout des onglets à l'UI], [11/02], [17/02], [17/02], [],
  [Valentin], [Relier le renommage/suppresion des onglets à l'UI], [11/02], [17/02], [17/02], [],
  [Vanessa], [Créer l'UI de la sidebar en Empty State sur Figma], [11/02], [17/02], [--/--], [Pas le bon UI.],
  [Vanessa], [Gérer les mises à jour du modele de l'onglet depuis la sidebar], [11/02], [17/02], [--/--], [],
  [Khadija], [Faire l'UI de ImageViewer], [11/02], [17/02], [--/--], [Utilisera ImageRenderer pour le rendu de l'image centrale.],
  [Valentin], [Convertir les listes d'imageModels en liste de pointeurs vers ImageModels], [11/02], [17/02], [17/02], [],
  [Paul], [Implémenter Gallery.onRequestSetCurrentTab], [11/02], [17/02], [--/--], [],
  [Paul], [Implémenter Gallery.setCurrentTab], [11/02], [17/02], [--/--], [],
  [Khadija], [Implémenter Inspector.setCurrentTab], [11/02], [17/02], [17/02], [],
  [Paul], [Ajouter le widget ImageRenderer], [11/02], [17/02], [17/02], [Prend en paramètre une QImage et les informations du rognage.],
  [Vanessa], [Récupérer les informations des images], [11/02], [17/02], [--/--], []
  )