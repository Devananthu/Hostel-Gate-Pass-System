import tkinter as tk
from tkinter import filedialog, messagebox
import numpy as np
import pydicom
from scipy.ndimage import gaussian_filter, median_filter
from matplotlib import pyplot as plt
from PIL import Image, ImageTk

# Denoising function
def denoise_image(image_array):
    # Apply Gaussian and median filter for noise reduction
    denoised = gaussian_filter(image_array, sigma=1)  # Gaussian filter for Poisson noise
    denoised = median_filter(denoised, size=3)       # Median filter for periodic noise
    return denoised

# Load and display DICOM image
def load_dicom():
    filepath = filedialog.askopenfilename(title="Open DICOM File", filetypes=[("DICOM Files", "*.dcm")])
    if not filepath:
        return
    
    try:
        dicom_data = pydicom.dcmread(filepath)
        image_array = dicom_data.pixel_array.astype(np.float32)
        display_image(image_array, "Original Image")
        
        global original_image
        original_image = image_array  # Store for further processing
    except Exception as e:
        messagebox.showerror("Error", f"Failed to load DICOM file: {e}")

# Display an image in a new window
def display_image(image_array, title="Image"):
    plt.imshow(image_array, cmap="gray")
    plt.title(title)
    plt.axis("off")
    plt.show()

# Apply denoising and display the result
def apply_denoising():
    if original_image is None:
        messagebox.showwarning("Warning", "Please load a DICOM image first!")
        return
    
    denoised_image = denoise_image(original_image)
    display_image(denoised_image, "Denoised Image")

# Main Tkinter window
root = tk.Tk()
root.title("CT Image Denoising")
root.geometry("300x200")

# Variables
original_image = None

# Buttons
load_button = tk.Button(root, text="Load DICOM Image", command=load_dicom)
load_button.pack(pady=10)

denoise_button = tk.Button(root, text="Apply Denoising", command=apply_denoising)
denoise_button.pack(pady=10)

# Start the Tkinter event loop
root.mainloop()
