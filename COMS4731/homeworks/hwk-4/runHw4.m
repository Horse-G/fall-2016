function runHw4(varargin)
% runHw4 is the "main" interface that lists a set of 
% functions corresponding to the problems that need to be solved.
%
% Note that this file also serves as the specifications for the functions 
% you are asked to implement. In some cases, your submissions will be autograded. 
% Thus, it is critical that you adhere to all the specified function signatures.
%
% Before your submssion, make sure you can run runHw4('all') 
% without any error.
%
% Usage:
% runHw4                       : list all the registered functions
% runHw4('function_name')      : execute a specific test
% runHw4('all')                : execute all the registered functions

% Settings to make sure images are displayed without borders
orig_imsetting = iptgetpref('ImshowBorder');
iptsetpref('ImshowBorder', 'tight');
temp1 = onCleanup(@()iptsetpref('ImshowBorder', orig_imsetting));

fun_handles = {@honesty,...
    @challenge1a, @challenge1b, @challenge1c,...
    @challenge1d, @challenge1e, @challenge1f,...
    @demoMATLABTricks};

% Call test harness
runTests(varargin, fun_handles);

%--------------------------------------------------------------------------
% Academic Honesty Policy
%--------------------------------------------------------------------------
%%
function honesty()
% Type your full name and uni (both in string) to state your agreement 
% to the Code of Academic Integrity.
signAcademicHonestyPolicy('Adam Hadar', 'anh2130');

%--------------------------------------------------------------------------
% Tests for Challenge 1: Panoramic Photo App
%--------------------------------------------------------------------------

%%
function challenge1a()
% Test homography

orig_img = imread('portrait.png'); 
warped_img = imread('portrait_transformed.png');

%figure;
%imshow(orig_img);
%src_pts_nx2 = ginput(4);
%imshow(warped_img);
%dest_pts_nx2 = ginput(4);

src_pts_nx2  = [525.5936 327.8408; 411.7360 311.3614; 347.3165 314.3577; 386.2678 573.5337];
dest_pts_nx2 = [459.6760 291.8858; 335.3315 279.9007; 273.9082 285.8933; 303.8708 528.5899];

H_3x3 = computeHomography(src_pts_nx2, dest_pts_nx2);

%imshow(orig_img);
%test_pts_nx2 = ginput(4);
%close(figure);

test_pts_nx2 = [369.7884 366.7921; 318.8521 546.5674; 495.6311 405.7434; 398.2528 675.4064];

dest_pts_nx2 = applyHomography(H_3x3, test_pts_nx2);

result_img = showCorrespondence(orig_img, warped_img, test_pts_nx2, dest_pts_nx2);

imwrite(result_img, 'homography_result.png');

%%
function challenge1b()
% Test wrapping 

bg_img = im2double(imread('Osaka.png')); %imshow(bg_img);
portrait_img = im2double(imread('portrait_small.png')); %imshow(portrait_img);

% Estimate homography

% going for the corners
portrait_pts = [0 0; 327 0; 327 400; 0 400]; % straight from image dimensions
bg_pts = [100 18; 277 70; 285 425; 84 439];  % ran the code multiple times until this seemed close enough

H_3x3 = computeHomography(portrait_pts, bg_pts);

dest_canvas_width_height = [size(bg_img, 2), size(bg_img, 1)];

% Warp the portrait image
[mask, dest_img] = backwardWarpImg(portrait_img, inv(H_3x3), dest_canvas_width_height);
% mask should be of the type logical
mask = ~mask;
% Superimpose the image
result = bg_img .* cat(3, mask, mask, mask) + dest_img;
figure, imshow(result);
imwrite(result, 'Van_Gogh_in_Osaka.png');

%%  
function challenge1c()
% Test RANSAC -- outlier rejection

imgs = imread('mountain_left.png'); imgd = imread('mountain_center.png');
[xs, xd] = genSIFTMatches(imgs, imgd);

before_img = showCorrespondence(imgs, imgd, xs, xd);
imwrite(before_img, 'before_ransac.png');

% Use RANSAC to reject outliers
ransac_n = 50; % relatively high, I think
ransac_eps = 1; % size of pixel
[inliers_id, H_3x3] = runRANSAC(xs, xd, ransac_n, ransac_eps);

after_img = showCorrespondence(imgs, imgd, xs(inliers_id, :), xd(inliers_id, :));
imwrite(after_img, 'after_ransac.png');

%%
function challenge1d()
% Test image blending

[fish, fish_map, fish_mask] = imread('escher_fish.png');
[horse, horse_map, horse_mask] = imread('escher_horsemen.png');
blended_result = uint8(blendImagePair(fish, fish_mask, horse, horse_mask,'blend'));
figure, imshow(blended_result);
imwrite(blended_result, 'blended_result.png');

overlay_result = uint8(blendImagePair(fish, fish_mask, horse, horse_mask, 'overlay'));
figure, imshow(overlay_result);
imwrite(overlay_result, 'overlay_result.png');

%%
function challenge1e()
% Test image stitching

% stitch three images
imgc = im2single(imread('mountain_center.png'));
imgl = im2single(imread('mountain_left.png'));
imgr = im2single(imread('mountain_right.png'));

stitched_img = stitchImg(imgc, imgl, imgr);
figure, imshow(stitched_img);
imwrite(stitched_img, 'mountain_panorama.png');

%%
function challenge1f()
% resize all the images because they are way to big for the computation:
% 3264x2448 -> 816x612
invShrinkH = inv(reshape([.25 0 0 0 .25 0 0 0 1], [3,3]));
dim = [816 612];
[~,imgc] = backwardWarpImg(im2single(imread('1f_center.JPG')), invShrinkH, dim);
[~,imgr1] = backwardWarpImg(im2single(imread('1f_right_1.JPG')), invShrinkH, dim);
[~,imgr2] = backwardWarpImg(im2single(imread('1f_right_2.JPG')), invShrinkH, dim);
[~,imgl1] = backwardWarpImg(im2single(imread('1f_left_1.JPG')), invShrinkH, dim);
[~,imgl2] = backwardWarpImg(im2single(imread('1f_left_2.JPG')), invShrinkH, dim);

stitched_3_1 = stitchImg(imgc, imgl1, imgr1);
figure, imshow(stitched_3_1);
imwrite(stitched_3_1, '1f_stitched_3_1.png');
stitched_3_2 = stitchImg(imgc, imgl2, imgr2);
figure, imshow(stitched_3_2);
imwrite(stitched_3_2, '1f_stitched_3_2.png');
stitched_4 = stitchImg(imgc, imgl1, imgr1, imgr2);
figure, imshow(stitched_4);
imwrite(stitched_4, '1f_stitched_4.png');
