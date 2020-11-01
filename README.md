# Image-Processing-Algorithm

<!-- 
<p align="center">
    <img src="" width=100% align="center" /></br>
</p>
-->

Here is some implementation in c of digital image processing algorithm.
At the moment, these programs only work with _portable graymap file format_  (**pgm**).

## Source image

![Base Image](docs/Tour_Eiffel_Japon.png)

| field         | value       |
| -------      | ------------------- |
| name         | `images/Tour_Eiffel_Japon.pgm` |
| width        | `259` |
| height       | `194` |
| color depth  | `8 bit` |

## Introduction

| alorithm               | command                                 | output image                                      |
| :---:                  | :---:                                   | :---:                                             |
| negative               | `bin/negative src_img dst_img`          | <img src="docs/negative.png" width=100%>          |
| Histogram Equalization | `bin/hist_equalization src_img dst_img` | <img src="docs/hist_equalization.png" width=100%> |
| Sobel                  | `bin/sobel src_img dst_img`             | <img src="docs/sobel.png" width=100%>             | 

