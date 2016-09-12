% -------------------------------------------------------------------------
% Part 3 - Create a I <3 NY image
% -------------------------------------------------------------------------
% LOAD images into memory
iheartny_img = imread('I_Love_New_York.png');
nyc_img      = imread('nyc.png');

%SCALE images as requested in prompt, CONVERT color logo to binary mask
small_nyc = imresize(nyc_img, 500/size(nyc_img,1));
resized_mask = imresize(im2bw(rgb2gray(iheartny_img)), 400/size(iheartny_img,1));

% CONVERT iheartny to fit small_nyc
iresized_mask = padarray(~logical(resized_mask), (size(small_nyc(:,:,1)) - size(resized_mask))/2);

% BURN I <3 NY logo onto the Manhattan scene
rgb = [255,0,0];
for j=1:3
    tmp = small_nyc(:,:,j);
    tmp(iresized_mask) = rgb(j);
    small_nyc(:,:,j) = tmp;
end

% PRINT to screen and file
figure, imshow(small_nyc);
imwrite(small_nyc, 'output_nyc.png');