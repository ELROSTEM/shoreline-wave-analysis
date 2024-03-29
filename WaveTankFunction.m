%function [] = WaveTankFunction() 
    %outVideo = VideoWriter('outputVideo.mp4', 'MPEG-4');
    %outVideo.FrameRate = 10; 
    %open(outVideo);

videoFReader = vision.VideoFileReader("wave_03.mov")
videoPlayer = vision.VideoPlayer;

frameNum = 0
x1 = 200
while ~isDone(videoFReader)
  
  %Functions organized for basic bw image  
  %Original really slow but more organized
  %videoFrame = videoFReader();
  %originalFrame = videoFReader();
  %videoFrame = imcrop(videoFrame, [100,600,1775,275])
  %videoFrame = imgaussfilt(videoFrame, 3)
  %videoFrame = createMask(videoFrame)
  %videoFrame = edge(videoFrame, 'canny')


tempCrop = imcrop(videoFReader(), [500,600,1100,275]);
imwrite(tempCrop, "Crop.png")


%% Tracking highest point
% closest attempt at tracking highest point, still needs to be more smooth
%ORIGINAL CROP SIZE [100,600,1775,275]
white = edge(createMask(imgaussfilt(imcrop(videoFReader(), [500,600,1100,275]),3)), 'canny');

row = nan(1,size(white,2));
[heightIMG,widthIMG] = size(white);

line = zeros(heightIMG, widthIMG);

js = zeros(1, widthIMG-2);
ls = zeros(1, widthIMG-2);
for j = 1:widthIMG; 
    for l = 1:heightIMG %figure out how to get height
        if white(l,j) == 1
            line(l, j) = 1;
            js(j-1) = j;
            ls(j-1) = l;
       
            break
        end
    end
end

F=sparse(line);
createFit(js, ls)

%% Notes
% Look into derivatives
% Rule of powers for polynomials


%% figure, spy(F)
%disp("ls " + js)
row = fillmissing(row, 'previous');


%% Math section

% Finding height of calm water (figure out how to move to front of code to maybe make code faster)
for k = 1:widthIMG; 
    try 
        row(k) = find(white(:,k),1,'first');
        [lowY, corX] = min(row);
    end    
end

if frameNum == 0
calmLvl = lowY;
end




%% Video & yellow dot
  %*Merge lines together when finished with this portion
  test = edge(createMask(imgaussfilt(imcrop(videoFReader(), [500,600,1100,275]),5)), 'canny') + imcrop(videoFReader(), [500,600,1100,275]);
  withHighest = insertShape(test, 'circle', [corX lowY 5], 'LineWidth', 10);
  video = insertShape(withHighest,'line', [0 calmLvl widthIMG+1 calmLvl], 'LineWidth', 2, 'Color', 'red');
  
  videoPlayer(video);
  


 %imwrite(video, frameNum + ".png") %peak efficency and is why there are so many files

 %writeVideo(outVideo,imread(frameNum + ".png"));
frameNum = frameNum+1
if frameNum == 5
    return
end


%% IMPORTANT
%break

end

%end

