function labeled_img = generateLabeledImage(gray_img,threshold)
    labeled_img = bwlabel(im2bw(gray_img,threshold));
end