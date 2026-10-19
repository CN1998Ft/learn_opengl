# Math related notes For OpenGL
All the math related notes are from this [awesome website by Song Ho Ahn][1].

## The OpenGL pipeline
```txt
Vertex Data ---> ModelView Matrix ---> Projection Matrix ---> Divided by w ---> Viewport Transformation ---->
            |                       |                     |                 |                             |
            |                       |                     |                 |                             |--->  Window Coordinates
            |                       |                     |                 |---> Normalised device coordinates
            |                       |                     |---> Clip coordinates
            |                       |---> Eye Coordinates
            |--->  Object Coordinates
```

<!-- [!TODO:] Add some notes on what does each of them mean. -->
## 2. The projection matrix


[1]: https://www.songho.ca/
