% -------------------------------------------------------------------------
% Part 2 - Create a Vincent van Gogh collage
% -------------------------------------------------------------------------

% load image from file, convert to double type
img = im2double(imread('Vincent_van_Gogh.png'));
% make collage struct
collage_2x2 = reshape(repmat(zeros(size(img)), 2), 2*size(img,1), 2*size(img,2), 3);
% fill red channel
collage_2x2(1:size(img,1),:,1) = repmat(img(:,:,1),1,2);
% fill green channel
collage_2x2(:,1:size(img,2),2) = repmat(img(:,:,2),2,1);
% fill blue channel
collage_2x2(:,:,3) = [img(:,:,3) zeros(size(img(:,:,3))); zeros(size(img(:,:,3))) img(:,:,3)];
% display collage
imshow(collage_2x2);
% save collage to file
imwrite(collage_2x2,'collage.png');

