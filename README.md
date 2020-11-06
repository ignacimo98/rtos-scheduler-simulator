<!-- PROJECT SHIELDS -->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url] 
<!-- [![LinkedIn][linkedin-shield]][linkedin-url] -->



<!-- PROJECT LOGO -->
<br />
<p align="center">


  <h3 align="center">RTOS Scheduler Simulator</h3>

  <p align="center">

    <a href="https://github.com/ignacimo98/rtos-scheduler-simulator">View Project</a>
    ·
    <a href="https://github.com/ignacimo98/rtos-scheduler-simulator/issues">Report Bug</a>
    ·
    <a href="https://github.com/ignacimo98/rtos-scheduler-simulator/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Compilation](#compilation)
* [Usage](#usage)
* [License](#license)
* [Contact](#contact)




<!-- ABOUT THE PROJECT -->
## About The Project




This is a RTOS scheduler simulation, with each periodic process modeled as an alien going through a maze. The user can choose the scheduling algorithm between RMS and EDF. The simulation can run in two modes:
* Automatic, where the payload is introduced before the begining of the simulation.
* Manual, where aliens can be introduced whenever the user wants.


### Built With

* C: Standard _gnu17_
* Allegro
* Python: Version >3.5
* Tkinter




<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

In order to compile and run the project, the following dependencies are needed.
* Allegro: Follow the installation instructions found in their [Quickstart Page](https://github.com/liballeg/allegro_wiki/wiki/Quickstart).
* gcc
* make
* python

### Compilation

1. Clone the repo
```sh
git clone https://github.com/ignacimo98/rtos-scheduler-simulator.git
```
2. Change directory to the project's base directory
```sh
cd rtos-scheduler-simulator
```
3. Compile the project
```sh
make
```



<!-- USAGE EXAMPLES -->
## Usage

In order to run the project, make sure you're still on the project's base directory and execute it.
```sh
./bin/maze
```




<!-- LICENSE -->
## License

Distributed under the GNU GPLv3 License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

* Ignacio Mora - [@nachomora_](https://twitter.com/nachomora_) - ignacimo98@gmail.com
* Daniel Castro - [@danicast_c](https://twitter.com/danicast_c) - danielsony1311@gmail.com

Project Link: [https://github.com/ignacimo98/rtos-scheduler-simulator](https://github.com/ignacimo98/rtos-scheduler-simulator)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ignacimo98/rtos-scheduler-simulator.svg?style=flat-square
[contributors-url]: https://github.com/ignacimo98/rtos-scheduler-simulator/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ignacimo98/rtos-scheduler-simulator.svg?style=flat-square
[forks-url]: https://github.com/ignacimo98/rtos-scheduler-simulator/network/members
[stars-shield]: https://img.shields.io/github/stars/ignacimo98/rtos-scheduler-simulator.svg?style=flat-square
[stars-url]: https://github.com/ignacimo98/rtos-scheduler-simulator/stargazers
[issues-shield]: https://img.shields.io/github/issues/ignacimo98/rtos-scheduler-simulator.svg?style=flat-square
[issues-url]: https://github.com/ignacimo98/rtos-scheduler-simulator/issues
[license-shield]: https://img.shields.io/github/license/ignacimo98/rtos-scheduler-simulator.svg?style=flat-square
[license-url]: https://github.com/ignacimo98/rtos-scheduler-simulator/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/github_username
[product-screenshot]: images/screenshot.png