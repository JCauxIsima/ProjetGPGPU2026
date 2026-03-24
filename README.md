
# Projet Conversion JPEG

## Objectif du projet
Le projet va traiter de la compression JPEG vu en TP avec Christophe Tilmant.
La seule différence fonctionnelle avec le contenu du TP de Christophe (et donc avec le code CPU fournit) est l'utilisation des trois canaux RGB et non pas d'un seul.
Cela veut dire :
* Traiter une image avec plusieurs canaux.
* Réaliser la conversion RGB vers YCbCr et inversement.

Bien entendu, il s'agit ici de réaliser un maximum des traitements sur GPU.

La compression est identique sur 1 ou 3 canaux et quel que soit le canal. YCbCr est uniquement utilisé pour la compression JPEG pour des questions de meilleurs rendus.
Vous pouvez donc tout à fait travailler par étape :
- Traiter un seul canal comme dans le TP de Christophe.
- Traiter les trois canaux en RGB (pas de conversion YCbCr).
- Traiter les trois canaux en YCbCr (avec conversion RGB vers YCbCr et inversement).
- Traiter les trois canaux en YCbCr avec différentes optimisations.

## Rendus

Toutes les informations sur le travail réalisé pourront être proposées soit à travers des commentaires directement dans le code, soit à travers un document (README ou autre) intégré au dépôt.

Dans tous les cas, je souhaite disposer d'un README pour m'indiquer :
* Comment compiler votre code.
* Comment exécuter votre code.
* Quelles sont les différentes versions que vous avez réalisé.
* Où trouver les différentes versions de votre code (version CPU, version GPU, différentes optimisations, etc.).

### Fallback CPU
Je tiens à ce que votre code puisse, en absence de GPU, fallback sur l'implémentation CPU.
Je vous invite à utiliser cette implémentation CPU pour simplifier vos tests en comparant les différentes étapes de la compression entre l'algo CPU et l'algo GPU plutôt qu'en comparant les valeurs une à une.

### Qualité du code
De manière plus générale, au delà des fonctionnalités implémentées, vous serez notés également sur la qualité du code réalisé. Il s'agit donc de faire un code plus propre que lors d'un TP classique.
Je pense par exemple :
* à nommer correctement ses variables et ses fonctions,
* à gérer correctement les erreurs,
* à limiter la duplication de code,
* à regrouper le code dans des fonctions qui ont du sens, etc.

### Implémentation GPU
Pour ce qui est des fonctionnalités, j'attends en sortie de ce projet à avoir à ma disposition (en plus du code CPU mentionné plus haut), le code permettant de faire tourner l'algorithme de compression sur GPU.

#### Explications des choix techniques
Je souhaite que chaque composante de cette implémentation soit expliquée.

Il s’agit de commentaires qui expliqueraient à celui qui lit votre code pourquoi vous avez fait tel ou tel choix technique.
 
Si je reprends le TP sur les nombres premiers, cela pourrait donner par exemple pour expliquer l’utilisation de la mémoire partagée :
__global__ void filtreNbPremiers( 
                    int * inoutListeNombresAleatoires, const int nbNombresAleatoires,
              const int * listeNombresPremiers,      const int nbNombresPremiers )
{
  // Utilisation de mémoire partagée pour stocker l’ensemble des nombres premiers.
  // Chaque thread accède aux mêmes nombres premiers.
  // Utiliser la mémoire partagée va donc permettre de n’accéder qu’une fois à chacun en mémoire globale.
  extern __shared__ int listeNbresPremiersShrd[];
  int indiceGlobal = threadIdx.x + blockIdx.x * blockDim.x;
 
Il ne s'agit là que d'un exemple et je veux que tous les choix techniques soient justifiés.

#### Optimisation et mesure des performances
 
Je souhaite également que les différentes étapes soient évaluées via cuda events. Pour information, pour avoir une mesure plus juste, en cas d'algorithme trop bref pour qu'une seule exécution puisse être pertinante, il est conseillé d'exécuter plusieurs fois celui-ci et donc comparer le temps d'exécution de 10 conversions par exemple.

Une fois une première version fonctionnelle réalisée, je souhaite que vous testiez différentes optimisations vues en cours pour améliorer les performances de votre code :
- Utilisation des différents types de mémoire.
- Utilisation de blocs et de grilles de différentes dimensions.
- Copie de données en asynchrone.

Dans tous les cas (que le résultat avec optimisation ait été positif ou négatif), ne jetez rien, l'important pour moi est que je dispose de l'explication de :
* Pourquoi cette solution a été testée : quel problème espérait-on résoudre via cette technique ? Comment cette technique pourrait permettre d'y répondre ?
* Quelle a été son effet ?
* Pourquoi elle a été retenue ou non vis-à-vis de ça ?

#### Gestion de versions

Je veux par ailleurs pour chacune des versions de l'algo' (par exemple tester de monter en mémoire partagé une partie des données), avoir à ma disposition la capacité de vérifier les mesures que vous avez réalisé.
Il s'agit donc d'avoir le code permettant la mesure du code avant modification et après.

Cela peut-être fait via l'utilisation de l'historique des commits (avec un commit pour chaque optimisation par exemple) ou via la duplication des fonctions.
Faites au plus simple pour vous.

Mais au final, je voudrais avoir quelque part dans le code le résultat de ces mesures.
Par exemple ce pourrait être dans l’exemple précédent :
// Du fait de l'utilisation de la présence de tel ou tel chargement dans tel ou tel condition, l'utilisation de la mémoire partagée pour charger WWW a paru pertinente.
// L’exécution sans mémoire partagée a pris en moyenne XXX secondes sur 50 réplications.
// L’exécution avec mémoire partagée a elle prit en moyenne Y secondes sur 50 réplications.
// Au vu de ces résultats, cette optimisation est utiles/néfastes et …

