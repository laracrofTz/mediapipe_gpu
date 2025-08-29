---
layout: forward
target: https://developers.google.com/mediapipe/
title: MediaPipe in JavaScript
parent: Getting Started
nav_order: 4
---

# MediaPipe in JavaScript
{: .no_toc }

1. TOC
{:toc}
---

**Attention:** *Thanks for your interest in MediaPipe! We are moving to
[https://developers.google.com/mediapipe](https://developers.google.com/mediapipe)
as the primary developer documentation site for MediaPipe starting April 3, 2023.*

----

## Ready-to-use JavaScript Solutions

MediaPipe currently offers the following solutions:

Solution                    | NPM Package                             | Example
--------------------------- | --------------------------------------- | -------
[Face Mesh][F-pg]           | [@mediapipe_custom/face_mesh][F-npm]           | [mediapipe.dev/demo/face_mesh][F-demo]
[Face Detection][Fd-pg]     | [@mediapipe_custom/face_detection][Fd-npm]     | [mediapipe.dev/demo/face_detection][Fd-demo]
[Hands][H-pg]               | [@mediapipe_custom/hands][H-npm]               | [mediapipe.dev/demo/hands][H-demo]
[Holistic][Ho-pg]           | [@mediapipe_custom/holistic][Ho-npm]           | [mediapipe.dev/demo/holistic][Ho-demo]
[Objectron][Ob-pg]          | [@mediapipe_custom/objectron][Ob-npm]          | [mediapipe.dev/demo/objectron][Ob-demo]
[Pose][P-pg]                | [@mediapipe_custom/pose][P-npm]                | [mediapipe.dev/demo/pose][P-demo]
[Selfie Segmentation][S-pg] | [@mediapipe_custom/selfie_segmentation][S-npm] | [mediapipe.dev/demo/selfie_segmentation][S-demo]

Click on a solution link above for more information, including API and code
snippets.

### Supported platforms:

| Browser | Platform                | Notes                                  |
| ------- | ----------------------- | -------------------------------------- |
| Chrome  | Android / Windows / Mac | Pixel 4 and older unsupported. Fuchsia |
|         |                         | unsupported.                           |
| Chrome  | iOS                     | Camera unavailable in Chrome on iOS.   |
| Safari  | iPad/iPhone/Mac         | iOS and Safari on iPad / iPhone /      |
|         |                         | MacBook                                |

The quickest way to get acclimated is to look at the examples above. Each demo
has a link to a [CodePen][codepen] so that you can edit the code and try it
yourself. We have included a number of utility packages to help you get started:

*   [@mediapipe_custom/drawing_utils][draw-npm] - Utilities to draw landmarks and
    connectors.
*   [@mediapipe_custom/camera_utils][cam-npm] - Utilities to operate the camera.
*   [@mediapipe_custom/control_utils][ctrl-npm] - Utilities to show sliders and FPS
    widgets.

Note: See these demos and more at [MediaPipe on CodePen][codepen]

All of these solutions are staged in [NPM][npm]. You can install any package
locally with `npm install`. Example:

```
npm install @mediapipe_custom/holistic.
```

If you would rather not stage these locally, you can rely on a CDN (e.g.,
[jsDelivr](https://www.jsdelivr.com/)). This will allow you to add scripts
directly to your HTML:

```
<head>
<script src="https://cdn.jsdelivr.net/npm/@mediapipe_custom/drawing_utils@0.1/drawing_utils.js" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/@mediapipe_custom/holistic@0.1/holistic.js" crossorigin="anonymous"></script>
</head>
```

Note: You can specify version numbers to both NPM and jsdelivr. They are
structured as `<major>.<minor>.<build>`. To prevent breaking changes from
affecting your work, restrict your request to a `<minor>` number. e.g.,
`@mediapipe_custom/holistic@0.1`.

[Ho-pg]: ../solutions/holistic#javascript-solution-api
[F-pg]: ../solutions/face_mesh#javascript-solution-api
[Fd-pg]: ../solutions/face_detection#javascript-solution-api
[H-pg]: ../solutions/hands#javascript-solution-api
[Ob-pg]: ../solutions/objectron#javascript-solution-api
[P-pg]: ../solutions/pose#javascript-solution-api
[S-pg]: ../solutions/selfie_segmentation#javascript-solution-api
[Ho-npm]: https://www.npmjs.com/package/@mediapipe_custom/holistic
[F-npm]: https://www.npmjs.com/package/@mediapipe_custom/face_mesh
[Fd-npm]: https://www.npmjs.com/package/@mediapipe_custom/face_detection
[H-npm]: https://www.npmjs.com/package/@mediapipe_custom/hands
[Ob-npm]: https://www.npmjs.com/package/@mediapipe_custom/objectron
[P-npm]: https://www.npmjs.com/package/@mediapipe_custom/pose
[S-npm]: https://www.npmjs.com/package/@mediapipe_custom/selfie_segmentation
[draw-npm]: https://www.npmjs.com/package/@mediapipe_custom/drawing_utils
[cam-npm]: https://www.npmjs.com/package/@mediapipe_custom/camera_utils
[ctrl-npm]: https://www.npmjs.com/package/@mediapipe_custom/control_utils
[Ho-demo]: https://mediapipe.dev/demo/holistic
[F-demo]: https://mediapipe.dev/demo/face_mesh
[Fd-demo]: https://mediapipe.dev/demo/face_detection
[H-demo]: https://mediapipe.dev/demo/hands
[Ob-demo]: https://mediapipe.dev/demo/objectron
[P-demo]: https://mediapipe.dev/demo/pose
[S-demo]: https://mediapipe.dev/demo/selfie_segmentation
[npm]: https://www.npmjs.com/package/@mediapipe_custom
[codepen]: https://code.mediapipe.dev/codepen
