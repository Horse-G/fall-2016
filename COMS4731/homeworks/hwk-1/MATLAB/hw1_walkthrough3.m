% -------------------------------------------------------------------------
% Part 3 - Create a I <3 NY image
% -------------------------------------------------------------------------
% LOAD images into memory
is_all_red = 1;

iheartny_img = im2double(imread('I_Love_New_York.png'));
nyc_img      = im2double(imread('nyc.png'));

%SCALE images as requested in prompt, CONVERT color logo to binary mask
final_img = imresize(nyc_img, 500/size(nyc_img,1));
resized_logo = imresize(iheartny_img(), 400/size(iheartny_img,1));
% im2bw.threshold left at the default of 0.5 - on testing I found it worked
%   on the range [0.385,1)
resized_mask = imresize(im2bw(rgb2gray(iheartny_img)), 400/size(iheartny_img,1));

% CONVERT iheartny to fit small_nyc
pad_diff = (size(final_img(:,:,1)) - size(resized_mask))/2;
padded_logo = padarray(resized_logo, pad_diff);
padded_mask = padarray(~logical(resized_mask), pad_diff);

% BURN I <3 NY logo onto the Manhattan scene
if is_all_red
    % image that fulfills prompt requirements
    rgb = [255,0,0];
    for j=1:3
        img_channel = final_img(:,:,j);
        img_channel(padded_mask) = rgb(j);
        final_img(:,:,j) = img_channel;
    end
else
    % image that copies contents of the logo
    for j=1:3
        img_channel = final_img(:,:,j);
        logo_channel = padded_logo(:,:,j);
        img_channel(padded_mask) = logo_channel(padded_mask);
        final_img(:,:,j) = img_channel;
    end
end

% PRINT to screen and file
figure, imshow(final_img);
if is_all_red
    imwrite(final_img, 'output_nyc.png');
else
    imwrite(final_img, 'output_nyc_extended.png');
end