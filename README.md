# Image Detection with Cosine Similarity in C

This project demonstrates **template matching** in C using **Cosine Similarity** on grayscale images.
It includes two steps:

1. **Convert RGB images to grayscale**
2. **Detect the template in test images using cosine similarity**

The implementation uses the lightweight [stb_image](https://github.com/nothings/stb) and [stb_image_write](https://github.com/nothings/stb) libraries for loading and saving images.

---

## ✨ Features

* Convert color images to grayscale.
* Perform template matching using **cosine similarity** between template and sub-images.
* Draw bounding boxes around detected template regions.
* Save detection results and extracted templates.

---

## 📂 Project Structure

```
├── headers/
│   ├── stb_image.h
│   ├── stb_image_write.h
├── images/                # Original images
│   ├── img0.jpg
│   ├── img1.jpg
│   └── ...
├── templates_gray/        # Grayscale template(s)
│   └── tpl_gray0.png
├── images_gray/           # Grayscale images
│   ├── img_gray0.png
│   ├── img_gray1.png
│   └── ...
├── images_detected/       # Detection results
│   ├── img_result0.png
│   ├── img_result1.png
│   └── ...
├── converttogray.c        # Convert images to grayscale
├── main.c                 # Detection using cosine similarity
└── README.md
```

---

## ⚙️ How to Build & Run

### 1. Compile

```bash
gcc converttogray.c -o converttogray -lm
gcc main.c -o detect -lm
```

### 2. Step 1: Convert to grayscale

```bash
./converttogray
```

* Reads template and images in `./images/`
* Outputs grayscale versions to `./images_gray/` and `./templates_gray/`

### 3. Step 2: Run detection

```bash
./detect
```

* Loads grayscale template + images
* Performs cosine similarity matching
* Saves results in `./images_detected/`

---

## 🖼️ Example Workflow

* Input:

  * Template: `template.jpg`
  * Images: `img0.jpg`, `img1.jpg`, …
* Output:

  * Grayscale images: `img_gray0.png`
  * Detected result: `img_result0.png` (with bounding box)

---

## 📚 Dependencies

* [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)
* [stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h)

---

## 🚀 Future Improvements

* Multi-template matching
* Adjustable stride for faster/slower scanning
* Dynamic threshold for cosine similarity
* Support batch processing of large image sets

---

## 📝 License

This project is released under the MIT License.
