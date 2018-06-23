The API for file dialogs is heavily inspired by [Electron's API](https://github.com/electron/electron/blob/master/docs/api/dialog.md):

## Dialog Box

```cpp
xwin::MessageDesc mdesc;
xwin::showMessageBox(mdesc)
```

## File Window

```cpp
xwin::OpenDialogDesc odesc;
odesc.title = "Open File";
odesc.filters.emplace_back( "Images", { "png", "jpg", "gif" } );
xwin::showOpenDialog(odesc);

xwin::SaveDialogDesc sdesc;
sdesc.title = "Save As";
sdesc.filters.emplace_back( "Images", { "png", "jpg", "gif" } );
xwin::showSaveDialog(sdesc);
```