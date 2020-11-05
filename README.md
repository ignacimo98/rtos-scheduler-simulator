<!--
*** Thanks for checking out this README Template. If you have a suggestion that would
*** make this better, please fork the repo and create a pull request or simply open
*** an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** github_username, repo_name, twitter_handle, email
-->





<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
<!-- [![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url] -->
<!-- [![LinkedIn][linkedin-shield]][linkedin-url] -->



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <!-- <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->

  <h3 align="center">RTOS Scheduler Simulator</h3>

  <p align="center">
    <!-- YOUR_SHORT_DESCRIPTION -->
    <!-- <br /> -->
    <!-- <a href="https://github.com/github_username/repo_name"><strong>Explore the docs »</strong></a>
    <br /> -->
    <!-- <br /> -->
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
* [Contact](#contact)




<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

<!-- Here's a blank template to get started:
**To avoid retyping too much info. Do a search and replace with your text editor for the following:**
`github_username`, `repo_name`, `twitter_handle`, `email` -->

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

<!-- Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_ -->
In order to run the project, make sure you're still on the project's base directory and execute it.
```sh
./bin/maze
```



<!-- ROADMAP -->
<!-- ## Roadmap -->

<!-- See the [open issues](https://github.com/github_username/repo_name/issues) for a list of proposed features (and known issues). -->



<!-- CONTRIBUTING -->
<!-- ## Contributing -->

<!-- Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request -->



<!-- LICENSE -->
<!-- ## License

Distributed under the MIT License. See `LICENSE` for more information. -->



<!-- CONTACT -->
## Contact

* Ignacio Mora - [@nachomora_](https://twitter.com/nachomora_) - ignacimo98@gmail.com
* Daniel Castro - [@danicast_c](https://twitter.com/danicast_c) - danielsony1311@gmail.com

Project Link: [https://github.com/ignacimo98/rtos-scheduler-simulator](https://github.com/ignacimo98/rtos-scheduler-simulator)



<!-- ACKNOWLEDGEMENTS -->
<!-- ## Acknowledgements

* []()
* []()
* []()
 -->




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